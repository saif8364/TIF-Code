#ifndef _LINEFOLLOW_H_
#define _LINEFOLLOW_H_

extern int strips_count;
extern bool is_line;

extern unsigned long previousMillis;
extern const unsigned long intervalMillis;

extern int S1[5];
extern int S2[5];

#define MID1 A14
#define MID2 A13

void linefollow(int speed = 50);
void linefollowUntil(int strips);
void linefollowEncoder(int ticks);
void linefollowWithFive(int speed = 50);
void linefollowFiveUntil(int strips);
void linefollowFiveEncoder(int ticks);
void finalDestination();
void startLineFollow();

void backLinefollow(int speed = 50);
void backLinefollowUntil(int strips);
void backLinefollowEncoder(int ticks);
void backLinefollowWithFive(int speed = 50);
void backLinefollowFiveUntil(int strips);
void backLinefollowFiveEncoder(int ticks);

#endif // _LINEFOLLOW_H_