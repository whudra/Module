#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <time.h>

#define DB_HOST "192.168.0.4"
#define DB_USER "root"
#define DB_PASS "1234"
#define DB_NAME "mydb"

int dbconnect(char* Serial_Number, char* state) {
	MYSQL* connection, conn;
    
    //time
    
    time_t timer;
    struct tm *t;
    char date[32]={0,};
    
    timer = time(NULL);
    t = localtime(&timer);
    
    sprintf(date, "%02d-%02d-%02d %02d:%02d:%02d", t->tm_year%100, t->tm_mon+1, t->tm_mday,
    t->tm_hour, t->tm_min, t->tm_sec);
    
    //time


	FILE* fp;
	unsigned long len, file_size;
	int query_stat;
	char* buf, * buf_to, * query;
	const char* stat = "INSERT INTO log(imagelog, Serial_Number, date, state) VALUES ""('%s', '%s', '%s', '%s')";

	//DB 초기화 및 접속
	mysql_init(&conn);
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	if (connection == NULL) {
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
		return EXIT_FAILURE;
	}
	else {
		printf("\nMysql connected\n");
	}
	//이미지를 불러오기
	fp = fopen("/home/pi/project/ExampleProgram/Doorlock/testimage.jpg", "rb");
	if (fp == NULL) {
		fprintf(stderr, "image open error");
		mysql_close(connection);
		return EXIT_FAILURE;
	}
	rewind(fp);
	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp); //파일의 사이즈를 찾음
	fseek(fp, 0, SEEK_SET);
	buf = (char*)malloc(file_size);
	fread(buf, sizeof(char), file_size, fp); //파일을 읽어와 buf에 참고
	fclose(fp);

	//이미지내 escape string 적용
	buf_to = (char*)malloc(file_size * 2 + 1);
	mysql_real_escape_string(connection, buf_to, buf, file_size);

	//Query 문 작성
	query = (char*)malloc(strlen(stat) + file_size * 2 + 1);
	len = snprintf(query, strlen(stat) + file_size * 2 + 1, stat, buf_to, Serial_Number, date, state);

	//Query 문 실행
	query_stat = mysql_real_query(connection, query, len);
	if (query_stat != 0) {
		fprintf(stderr, "Mysql query error : %s\n", mysql_error(&conn));
	}

	//할당한 메모리 반환
	free(buf);
	free(buf_to);
	free(query);

	//DB 커넥션 닫기
	mysql_close(connection);
	return EXIT_SUCCESS;
}
