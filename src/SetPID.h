unsigned long dt, tpre = 0;
//-----SET he so PID o day-----------------
float Kp = 9;
float Ki = 0;
float Kd = 0.05; // dt=80
float Kv = 0; 
//motorController.move(255 * (0.6 - Kv * abs(D)));
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
