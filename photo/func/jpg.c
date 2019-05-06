#include"linklist.h"
int jpg_display(char*s)
{
	struct jpeg_decompress_struct dinfo;
	struct jpeg_error_mgr jerr;
	dinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&dinfo);
	
	
	FILE*infile;
	infile = fopen(s,"r");
	if(infile == NULL)
	{
		perror("jpgopen error:");
		return -1;
	}
	
	jpeg_stdio_src(&dinfo,infile);
	
	jpeg_read_header(&dinfo,TRUE);
	
	jpeg_start_decompress(&dinfo);
	
	unsigned char *buffer = malloc(dinfo.output_width*dinfo.output_components);
	
	int x,y=0;
	while(dinfo.output_scanline<dinfo.output_height)
	{
		y=dinfo.output_scanline;
		jpeg_read_scanlines(&dinfo,&buffer,1);
		unsigned char a,b,g,r;
		int color;
		char*p=buffer;
		for(x=0;x<dinfo.output_width;x++)
		{
			if(dinfo.output_components==3)
			{
				a=0;
				
			}
			else
			{
				a=*(p++);
			}
			r=*(p++);
			g=*(p++);
			b=*(p++);
			color = a<<24|r<<16|g<<8|b;
			Draw_point(y,x,color);
			
		}
	}
	jpeg_finish_decompress(&dinfo);
	jpeg_destroy_decompress(&dinfo);
		
	free(buffer);
		
	fclose(infile);
}
/*
int main(int argc,char**argv)
{
	//step1:初始化lcd
	Init_lcd();
	
	//step2:显示JPG图片
	jpg_display(argv[1]);
	
	//step3:解映射
	close_lcd();
	
}
*/