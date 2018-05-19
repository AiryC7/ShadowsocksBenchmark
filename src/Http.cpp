#include "Http.h"

static size_t write_to_stringstream(void *contents,size_t size,size_t nmemb,void *handle) {
	stringstream *stream = (stringstream *) handle;
	size_t real_size = size * nmemb;

	stream->write((char *) contents,real_size);

	return real_size;
}

static size_t write_to_empty(void *contents,size_t size,size_t nmemb,void *handle) {
	return size * nmemb;
}

static int64_t current_millis(void) {
	struct timeval result;
	gettimeofday(&result,NULL);
	return result.tv_sec * 1000 + result.tv_usec / 1000;
}

string Http::text(const string &url,int timeout,const string &proxy, const string &dns) {
	CURL *curl;
	CURLcode result;
	stringstream stream;

	if (( curl = curl_easy_init() ) == nullptr )
		throw Exception("Curl init failure");

	curl_easy_setopt(curl,CURLOPT_URL,url.c_str());
	curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,&write_to_stringstream);
	curl_easy_setopt(curl,CURLOPT_WRITEDATA,&stream);
	curl_easy_setopt(curl,CURLOPT_TIMEOUT,timeout);
	curl_easy_setopt(curl,CURLOPT_DNS_SERVERS,dns.c_str());

	result = curl_easy_perform(curl);

	curl_easy_cleanup(curl);

	if ( result != CURLE_OK )
		throw Exception("Download " + url + " failure.");

	return stream.str();
}

int64_t Http::ping(const string &url,int timeout,const string &proxy,const string &dns) {
	CURL *curl = curl_easy_init();
	CURLcode result;

	curl_easy_setopt(curl,CURLOPT_URL,url.c_str());
	curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,&write_to_empty);
	curl_easy_setopt(curl,CURLOPT_TIMEOUT,timeout);
	curl_easy_setopt(curl,CURLOPT_PROXY,proxy.c_str());
	curl_easy_setopt(curl,CURLOPT_DNS_SERVERS,dns.c_str());

	int64_t begin = current_millis();
	result = curl_easy_perform(curl);
	int64_t delay = current_millis() - begin;

	curl_easy_cleanup(curl);

	if ( result == CURLE_OK )
		return delay;
	else 
		throw Exception("Timeout");
}

Http::CurlGlobalHandle::CurlGlobalHandle(void) noexcept {
	curl_global_init(CURL_GLOBAL_DEFAULT);
}

Http::CurlGlobalHandle::~CurlGlobalHandle(void) noexcept {
	curl_global_cleanup();
}

Http::CurlGlobalHandle Http::CurlGlobalHandle::handle;
