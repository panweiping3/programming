#include <iostream>
#include <QDebug>

#include <openssl/sha.h>

using namespace std;
#define BIG_FILE_UUID_LENGTH	(SHA_DIGEST_LENGTH * 2)	
#define BIG_FILE_BLOCK_SIZE	(512 * 1024)
#define BIG_FILE_ENTRY_SIZE	((BIG_FILE_UUID_LENGTH) + (BIG_FILE_BLOCK_SIZE))
#define BIG_FILE_SAFE_SIZE	(512 * 1024 * 1024)
#define BIG_FILE_OVERFLOW       ((qint64)1 << 32)
//#define BIG_FILE_OVERFLOW     (4 * 1024 * 1024 * 1024)
// 这样是不行的。因为计算过程中发生了整数溢出。
#define BIG_FILE_MAX_SIZE	(BIG_FILE_OVERFLOW - (BIG_FILE_SAFE_SIZE))
#define BIG_FILE_ENTRY_COUNT	((BIG_FILE_MAX_SIZE) / (BIG_FILE_ENTRY_SIZE))

int main(int argc, char *argv[])
{
	qDebug() << sizeof(long long);
	qDebug() <<__FILE__ << __LINE__ << __func__ << BIG_FILE_UUID_LENGTH; 
	qDebug() <<__FILE__ << __LINE__ << __func__ << BIG_FILE_BLOCK_SIZE; 
	qDebug() <<__FILE__ << __LINE__ << __func__ << BIG_FILE_ENTRY_SIZE; 
	qDebug() <<__FILE__ << __LINE__ << __func__ << BIG_FILE_SAFE_SIZE; 
	qDebug() <<__FILE__ << __LINE__ << __func__ << BIG_FILE_OVERFLOW; 
	qDebug() <<__FILE__ << __LINE__ << __func__ << BIG_FILE_MAX_SIZE; 
	qDebug() <<__FILE__ << __LINE__ << __func__ << BIG_FILE_ENTRY_COUNT; 


	qDebug() <<__FILE__ << __LINE__ << __func__ << (long long)BIG_FILE_UUID_LENGTH; 
	qDebug() <<__FILE__ << __LINE__ << __func__ << (long long)BIG_FILE_BLOCK_SIZE; 
	qDebug() <<__FILE__ << __LINE__ << __func__ << (long long)BIG_FILE_ENTRY_SIZE; 
	qDebug() <<__FILE__ << __LINE__ << __func__ << (long long)BIG_FILE_SAFE_SIZE; 
	qDebug() <<__FILE__ << __LINE__ << __func__ << (long long)BIG_FILE_OVERFLOW;
	qDebug() <<__FILE__ << __LINE__ << __func__ << (long long)BIG_FILE_MAX_SIZE; 
	qDebug() <<__FILE__ << __LINE__ << __func__ << (long long)BIG_FILE_ENTRY_COUNT; 

 	return 0;   
}
