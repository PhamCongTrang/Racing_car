unsigned long dt, tpre;
//-----SET he so PID o day-----------------
float Kp = 5;
float Ki = 0;
float Kd = 0;
float Kv = 0; 
/* 
Kv là hệ số giảm tốc khi vào cua
Kv = 0 thì xe giữ nguyên tốc độ khi vào cua
Kv càng lớn, xe càng giảm tốc độ, tỉ lệ với tan góc cua
*/
float errnow, errpre;
float P, I = 0, D;
// Khai bao bien goc quay do line
int goc;
int v;
int error;
int position;
int mode=0;
float sum;
int dem;
