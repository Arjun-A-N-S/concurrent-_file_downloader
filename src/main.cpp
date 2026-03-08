/******************************
* File			: main.cpp
* Author		: Arjun A N S
* Date			: 2026-03-07
* Description		: This is main cpp file 
******************************/
#include <iostream>
#include <cstdio>
#include <curl/curl.h>

size_t write_data(void *ptr,size_t size, size_t nmemb,FILE *stream){
	return fwrite(ptr, size, nmemb, stream);
}

int main(int argc, char *argv[]){
	if (argc != 3){
		std::cout << "Usage: ./downloader <URL> <output_file>\n";
	}
	const char* url  	= argv[1];
	const char* filename	= argv[2];
	CURL *curl;
	FILE* fp;
	CURLcode res;
	curl = curl_easy_init();
	if (curl) {
		fp = fopen(filename, "wb");
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		res = curl_easy_perform(curl);
		if (res != CURLE_OK) std::cout << "Download failed:" << curl_easy_strerror(res) << std::endl;
		curl_easy_cleanup(curl);
		fclose(fp);
	}
	std::cout << "Download finished!\n";
	return 0;
}
