/*
 * tdecode.cpp
 *
 *  Created on: Feb 4, 2013
 *      Author: sijiewang
 */

#include "tdecoder.h"
#include <iostream>

namespace mx {
//--------------------------------------------------------------------
void *do_fill_packets(void *arg) {
	TDecoder *td = (TDecoder *) arg;

	while (!td->m_thread_quit) {
		pthread_mutex_lock(&td->m_mutex);
		{
			// 如果数据缓冲满了，就等下一轮
			if (!td->_is_open() || td->_is_full()) {
				goto END;
			}
			// 准备读取
			AVPacket *avp = new AVPacket();
			// 开始读取
			int ret;
			// 如果读取错误 ...
			if ((ret = av_read_frame(td->m_pFormatCtx, avp)) < 0) {
				// 文件结尾,那么重头开始循环
				if (ret == AVERROR_EOF) {
					td->_move_to_begin();
					ret = av_read_frame(td->m_pFormatCtx, avp);
					if (ret < 0) {
						goto END;
					}
				}
				// 否则打印错误 。。。
				else {
					cout << "fail to read pack (" << ret << ")" << endl;
					goto END;
				}
			}
			// 读取成功，则将数据包压入缓冲
			int off = td->m_pack_index + (td->m_pack_size++);
			if (off > td->m_pack_maxlen) {
				off = off - td->m_pack_maxlen;
			}
			td->m_packets[off] = avp;
		}
		END: pthread_mutex_unlock(&td->m_mutex);
		// 等待 10ms
		ThreadWaitMs(&td->m_cond, &td->m_mutex_cond, 10);
	}
	return NULL;
}
//--------------------------------------------------------------------
//	struct vdpau_render_state *render = (struct vdpau_render_state*)frame->data[0];
//	VdpVideoSurface videoSurface = render->surface;
AVFrame *TDecoder::decode() {
	AVFrame *avf = NULL;
	pthread_mutex_lock(&m_mutex);
	{
		if (_is_empty()) {
			goto END;
		}
		// 首先得到一个 packet
		AVPacket *avp = m_packets[m_pack_index++];

		// 分配一桢的内存
		avf = avcodec_alloc_frame();

		// 进行转换
		int finished;
		avcodec_decode_video2(m_codecContext, avf, &finished, avp);

		// 记数减1
		m_pack_size--;
	}
	END: pthread_mutex_unlock(&m_mutex);
	return avf;
}
//--------------------------------------------------------------------
void TDecoder::open(string &path) {
	pthread_mutex_lock(&m_mutex);
	{
		if (_is_open())
			_close();
		// 设置文件名
		char *cs = path.c_str();

		// 尝试打开文件，返回如果不是 0 表示错误
		int avret = avformat_open_input(&m_pFormatCtx, cs, NULL, NULL);
		// 进入正常流程
		if (avret == 0) {
			m_videoIndex = -1;
			// 记住新的文件名
			m_filePath = string(cs);
			// 打印视频信息
			av_dump_format(m_pFormatCtx, 0, cs, 0);

			// 找到视频流中视频的 index （可能还有音频等 ...）
			for (unsigned int i = 0; i < m_pFormatCtx->nb_streams; i++) {
				if (m_pFormatCtx->streams[i]->codec->codec_type
						== AVMEDIA_TYPE_VIDEO) {
					m_videoIndex = i;
					break;
				}
			}
			if (m_videoIndex < 0) {
				cout << " ! fail to found video index!" << endl;
				goto END;
			}

			// 最后清空包缓冲
			_clear_packets();

			// 得到解码器 TODO 现在写死是 H.264 的
			m_stream = m_pFormatCtx->streams[m_videoIndex];

			m_codecContext = m_stream->codec;
			if (m_codecContext->codec_id == CODEC_ID_H264) {
				// 采用硬件解码
				m_codec = avcodec_find_decoder_by_name("h264_vdpau");

				// 设置解码器的处理方法
				m_codecContext->get_format = decoder_get_format;
				m_codecContext->get_buffer = decoder_get_buffer;
				m_codecContext->release_buffer = decoder_release_buffer;
				m_codecContext->draw_horiz_band = decoder_draw_horiz_band;
				m_codecContext->reget_buffer = decoder_get_buffer;
				m_codecContext->slice_flags = SLICE_FLAG_CODED_ORDER
						| SLICE_FLAG_ALLOW_FIELD;

				// 打开解码器？ 怎么关上呢？
				int openRet;
				if ((openRet = avcodec_open2(m_codecContext, m_codec, NULL))
						< 0) {
					cout << "fail to open codec! " << openRet << endl;
				}

				// 创建 FrameBuffer
				int width = m_codecContext->coded_width;
				int height = m_codecContext->coded_height;

				VdpStatus vdp_st = m_vdpau->vdp_video_surface_create(
						m_vdpau->vdpDevice, VDP_CHROMA_TYPE_420, width,
						height, &m_surface_render[i].surface);
				if (vdp_st != VDP_STATUS_OK) {
					fprintf(stderr, "vdp_video_surface_create failed with %d\n",
							vdp_st);
					m_pVdpContext->vdp_video_surface_destroy(
							m_surface_render[i].surface);
					m_surface_render[i].surface = VDP_INVALID_HANDLE;
					return -1;
				}

			}
			// 不支持 !!! TODO 是否应该清空打开的东东捏？
			else {
				cout << "Unsupport codec! " << m_codecContext->codec_name
						<< endl;
			}
		}
		// 出错的话打印错误信息
		else {
			cout << " ! TDecoder fail to open (" << avret << ") '" << path
					<< "'!" << endl;
		}
	}
	END: pthread_mutex_unlock(&m_mutex);
	// 尝试唤醒读取线程
	ThreadAwake(&m_cond, &m_mutex_cond);
}
//--------------------------------------------------------------------
void TDecoder::moveToBegin() {
	pthread_mutex_lock(&m_mutex);
	{
		_move_to_begin();
	}
	pthread_mutex_unlock(&m_mutex);
}
//--------------------------------------------------------------------
void TDecoder::_move_to_begin() {
	if (_is_open()) {
		int64_t timestamp;
		timestamp = 1 * AV_TIME_BASE;
		timestamp = av_rescale_q(timestamp, AV_TIME_BASE_Q,
				m_pFormatCtx->streams[m_videoIndex]->time_base);
		av_seek_frame(m_pFormatCtx, m_videoIndex, timestamp,
				AVSEEK_FLAG_BACKWARD);
	}
}
//--------------------------------------------------------------------
bool TDecoder::isOpen() {
	bool re = false;
	pthread_mutex_lock(&m_mutex);
	{
		re = _is_open();
	}
	pthread_mutex_unlock(&m_mutex);
	return re;
}
//--------------------------------------------------------------------
bool TDecoder::isFull() {
	bool re = false;
	pthread_mutex_lock(&m_mutex);
	{
		re = _is_full();
	}
	pthread_mutex_unlock(&m_mutex);
	return re;
}
//--------------------------------------------------------------------
bool TDecoder::isEmpty() {
	bool re = false;
	pthread_mutex_lock(&m_mutex);
	{
		re = _is_empty();
	}
	pthread_mutex_unlock(&m_mutex);
	return re;
}
//--------------------------------------------------------------------
void TDecoder::close() {
	pthread_mutex_lock(&m_mutex);
	{
		_close();
	}
	pthread_mutex_unlock(&m_mutex);
}
//--------------------------------------------------------------------
void TDecoder::_close() {
	if (_is_open()) {
		// 关闭输入流
		avformat_close_input(&m_pFormatCtx);
		// 清除缓冲区
		_clear_packets();
	}
}
//--------------------------------------------------------------------
bool TDecoder::_is_open() {
	return NULL != m_pFormatCtx;
}
//--------------------------------------------------------------------
bool TDecoder::_is_full() {
	return m_pack_size >= m_pack_maxlen;
}
//--------------------------------------------------------------------
bool TDecoder::_is_empty() {
	return m_pack_size == 0;
}
//--------------------------------------------------------------------
void TDecoder::_clear_packets() {
	for (int i = 0; i < m_pack_maxlen; i++) {
		AVPacket * avp = m_packets[i];
		if (NULL != avp) {
			av_free_packet(avp);
			av_freep(&avp);
		}
	}
	m_pack_index = 0;
	m_pack_size = 0;
}
//--------------------------------------------------------------------
TDecoder::TDecoder(int packsz, VdpauContext *vdpau) {
	m_packets = new AVPacket *[packsz];
	m_pack_maxlen = packsz;
	m_pack_index = 0;
	m_pack_size = 0;

	for (int i = 0; i < m_pack_maxlen; i++) {
		m_packets[i] = NULL;
	}

	m_pFormatCtx = NULL;

	m_thread_quit = false;

	m_vdpau = vdpau;

	pthread_mutex_init(&m_mutex, NULL);
	pthread_cond_init(&m_cond, NULL);
	pthread_mutex_init(&m_mutex_cond, NULL);
}
//--------------------------------------------------------------------
TDecoder::~TDecoder() {
	if (isOpen())
		close();
	// ...
	pthread_mutex_destroy(&m_mutex);
	pthread_cond_destroy(&m_cond);
	pthread_mutex_destroy(&m_mutex_cond);
}
//--------------------------------------------------------------------
extern "C" int decoder_get_buffer(struct AVCodecContext *c, AVFrame *pic) {
	VdpauDecoderContext *decoderContext = (VdpauDecoderContext*) c->opaque;
	struct vdpau_render_state *rndr = decoderContext->get_video_surface();
	int tryCount = 0;
	while ((rndr == NULL) && tryCount < (VIDEO_SURFACES_NUM / 2)) {
		rndr = decoderContext->get_video_surface();
		tryCount++;
	}
	pic->data[0] = (uint8_t*) rndr;
	if (pic->reference) {
		decoderContext->ip_age[0] = decoderContext->ip_age[1] + 1;
		decoderContext->ip_age[1] = 1;
		decoderContext->b_age++;
	} else {
		decoderContext->ip_age[0]++;
		decoderContext->ip_age[1]++;
		decoderContext->b_age = 1;
	}
	pic->type = FF_BUFFER_TYPE_USER;
	return 0;
}
//--------------------------------------------------------------------
extern "C" void decoder_release_buffer(struct AVCodecContext *c, AVFrame *pic) {
	struct vdpau_render_state *rndr = (struct vdpau_render_state*) pic->data[0];
	rndr->state &= ~FF_VDPAU_STATE_USED_FOR_REFERENCE;
	pic->data[0] = NULL;
}
//--------------------------------------------------------------------
extern "C" void decoder_draw_horiz_band(struct AVCodecContext *c,
		const AVFrame *frame, int offset[4], int y, int type, int h) {
	struct vdpau_render_state *rndr =
			(struct vdpau_render_state*) frame->data[0];
	VdpauDecoderContext *decoderContext = (VdpauDecoderContext*) c->opaque;
	decoderContext->decoder_render(rndr);
}
//--------------------------------------------------------------------
extern "C" enum PixelFormat decoder_get_format(AVCodecContext *codecCtx,
		const enum PixelFormat *pix_fmt) {
	for (int i = 0; pix_fmt[i] != PIX_FMT_NONE; i++)
		fprintf(stderr, "%d\t", pix_fmt[i]);
	return pix_fmt[0];
}
} /* namespace mx */

