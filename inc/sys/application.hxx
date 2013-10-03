#pragma once

class application
{
public:
  static application & instance(void);
  int run(void);
private:
  application(void);
  application(application const &);
  application & operator= (application const &);
  ~application(void) {}
};
