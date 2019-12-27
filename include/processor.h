#ifndef PROCESSOR_H
#define PROCESSOR_H


class Processor {
 public:
  float Utilization();  
  float User();
  float Nice();
  float System();
  float Idle();
  float IOwait();
  float IRQ();
  float SoftIRQ();
  float Steal();
  float Guest();
  float GuestNice();
  float TotalJiffies();
  float ActiveJiffies();
  float IdleJiffies();

};

#endif