unsigned long dt, tpre;
//-----SET he so PID o day-----------------
int Kp = 0.015;
int Ki = 0;
int Kd = 0;
int Kv = 0; 
/* 
Kv là hệ số giảm tốc khi vào cua
Kv = 0 thì xe giữ nguyên tốc độ khi vào cua
Kv càng lớn, xe càng giảm tốc độ, tỉ lệ với tan góc cua
*/
int errnow, errpre;
int P, I = 0, D;
// Khai bao bien goc quay do line
int goc;
int v;
int error;