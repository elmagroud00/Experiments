#include "Jpeg.h"

void LoadJpgTextureGL(char *file)
{
	FILE *jpefile;
	int sizebuf;
	unsigned char* buffer;
	unsigned char* texturebuf;
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	if((jpefile = fopen(file,"rb"))==NULL)
	{
		perror("fopen jpeg");
		return; 
	}
	jpeg_stdio_src(&cinfo,jpefile);
	jpeg_read_header(&cinfo,TRUE);
	jpeg_start_decompress(&cinfo);

	sizebuf = cinfo.output_width * cinfo.output_components;
	buffer = (unsigned char *)malloc(sizebuf);
	texturebuf = (unsigned char *)malloc(sizebuf * cinfo.output_height);
	unsigned char *tempjpg = texturebuf;
	while(cinfo.output_scanline < cinfo.output_height)
	{
		jpeg_read_scanlines(&cinfo,&buffer,1);
		memcpy(texturebuf,buffer,sizebuf);
		texturebuf +=sizebuf;
	}
	texturebuf = tempjpg;
	PushQueue(&JpgQueue, texturebuf, cinfo.output_width, cinfo.output_height);

	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);

	free(buffer);
	fclose(jpefile);
/*
//	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,cinfo.output_width,cinfo.output_height,0,GL_RGB,GL_UNSIGNED_BYTE,texturebuf);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	printf("load jpeg texture ok\n");

	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	free(texturebuf);
	free(buffer);
	*/
}
