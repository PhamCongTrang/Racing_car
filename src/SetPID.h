unsigned long dt, tpre = 0;
//-----SET he so PID o day-----------------
float Kp = 9; //Kp < 10 se khong ket
float Ki = 0;
float Kd = 0;//.05 // dt=40
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
int mode=1; // Digital or Analog
float sum;
int dem;
int FULL=1; // Full or Line follower

int demQuay = 0;
int demLan = 0;

unsigned long lineout = 0;