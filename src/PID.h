#ifndef PID_H
#define PID_H
#include <vector>


class PID {
 public:
  /**
   * Constructor
   */
  PID();

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Initialize PID.
   * @param (Kp_, Ki_, Kd_) The initial PID coefficients
   */
  void Init(double Kp_, double Ki_, double Kd_);

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   */
  void UpdateError(double cte);

  /**
   * Calculate the total PID error.
   * @output The total PID error
   */
  double TotalError(double cte);
  void Twidel();

 private:
  /**
   * PID Errors
   */
  double p_error;
  double prev_err;
  double i_error;
  double d_error;
  double best_err;
  double total_error;
  int counter;
  

  /**
   * PID Coefficients
   */ 
  double Kp;
  double Ki;
  double Kd;
  
  double dp_p;
  double dp_d;
  double dp_i;
  double current_err;
  int param;
  
  bool change;
};

#endif  // PID_H