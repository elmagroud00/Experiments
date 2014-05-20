/*
 * tdecoder.h
 *
 *  Created on: Feb 4, 2013
 *      Author: sijiewang
 */

#ifndef TDECODER_H_
#define TDECODER_H_

// ~ ffmpeg & vdpau etc ...
extern "C" {
#include <libavutil/common.h>
#include <libavutil/avstring.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libavcodec/vdpau.h>
#include <vdpau/vdpau_x11.h>
#include <libswscale/swscale.h>
} // ~ ffmpeg & vdpau etc ...

#include <string>
#include <list>
#include <pthread.h>

using namespace std;

namespace mx {
//--------------------------------------------------------------------
extern "C" int decoder_get_buffer(struct AVCodecContext *c, AVFrame *pic);
extern "C" void decoder_release_buffer(struct AVCodecContext *c, AVFrame *pic);
extern "C" void decoder_draw_horiz_band(struct AVCodecContext *context,
		const AVFrame *frame, int offset[4], int y, int type, int h);
extern "C" enum PixelFormat decoder_get_format(struct AVCodecContext *codecCtx,
		const enum PixelFormat *pix_fmt);

//--------------------------------------------------------------------
class TDecoder {
public:
	friend void *do_fill_packets(void *);
	TDecoder(int packsz, VdpauContext *vdpau);
	~TDecoder();

	// 打开，一个文件，并开始启动数据包填充线程
	// 如果正在打开一个文件，首先关闭，再打开新的文件
	// 【注】线程安全
	void open(string &path);

	// 将视频的包读取流部分移动到开头
	void moveToBegin();

	// 判断是否打开了一个文件
	bool isOpen();
	// 判断数据包缓冲区是否已满
	bool isFull();
	// 判断数据包缓冲区是否为空
	bool isEmpty();
	// 关闭一个文件，将会停止数据包填充线程，但是它并不清空已经解压的队列
	// 【注】线程安全
	void close();

	// 从数据包缓冲中解压一个数据包并返回给调用者
	// 如果数据包缓冲中木有数据了，则返回 NULL
	// 【注】线程安全
	AVFrame *decode();

protected:
	// 非线程安全的方法关闭文件
	void _close();

	// 非线程安全的方法判断是否文件是打开的
	bool _is_open();

	// 非线程安全的方法判断数据缓冲区是否满
	bool _is_full();
	// 非线程安全的方法判断数据缓冲区时候为空
	bool _is_empty();

	// 非线程安全的清楚数据包缓冲
	void _clear_packets();

	// 非线程安全的将视频的包读取流部分移动到开头
	void _move_to_begin();

	VdpauContext *m_vdpau;    // 封装了 vdpau 的操作函数

	string m_filePath;		// 打开的文件路径

	AVPacket **m_packets;	// 数据包缓冲
	int m_pack_maxlen;      // 缓冲大小
	int m_pack_index;       // 缓冲下标，读一个则 ++
	int m_pack_size;        // 缓冲中可用数据的数量

private:
	pthread_mutex_t m_mutex;	// 整个类的函数共用一把锁
	pthread_cond_t m_cond;		   // 一个通知信号量，用来唤醒包准备线程
	pthread_mutex_t m_mutex_cond;  // 信号量的读写锁

	AVFormatContext *m_pFormatCtx;  // 视频格式上下文指针，如果文件关闭，则为 NULL
	int m_videoIndex;               // 视频流中视频的 index
	pthread_t m_thread;             // 针对文件数据包的解码线程
	AVCodec *m_codec;               // 当前文件要用到的解码器，当 open 的时候被准备
	AVStream *m_stream;              // 当前文件流
	AVCodecContext *m_codecContext; // 当前流的解码器上下文对象

	bool m_thread_quit;         // 标识读包线程是否要退出
};
//--------------------------------------------------------------------
// 线程回调函数，用来填充 TDecoder 的 m_packets
void *do_fill_packets(void *arg);
//--------------------------------------------------------------------
} /* namespace mx */

#endif /* TDECODER_H_ */
