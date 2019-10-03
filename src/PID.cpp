#include "PID.h"
#include <iostream>
using namespace std;
/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
  this -> Kp = Kp_;
  this -> Ki = Ki_;
  this -> Kd = Kd_;
  
  this -> p_error = 0;
  this -> d_error = 0;
  this -> i_error = 0;
  this -> prev_err = 0;
  this -> best_err = 1000000;
  p.push_back(0);
  p.push_back(0);
  p.push_back(0);
  dp.push_back(1.0);
  dp.push_back(1.0);
  dp.push_back(1.0);

}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */
  
  p_error = cte;
  d_error = p_error - prev_err;
  prev_err = cte;
  i_error += prev_err;
}

double PID::TotalError(double cte) {
  /**
   * TODO: Calculate and return the total error
   */
  
  total_error += cte*cte;
  Twidel();
  
  return (Kp*p_error + Kd*d_error + Ki* i_error);  // TODO: Add your total error calc here!
}

void PID::Twidel(){
  
  
  std::cout << "Here " << std::endl;
  double sum = 0;
  for (int i=0;i<3;i++){
    sum+=dp[i];
  }
  if (sum > 0.000001 ){
  
  for (int i=0;i<3;i++){
    
  if ( total_error < best_err){
    p[i] += dp[i];
    dp[i] *= 1.1;
    
  }
    else {
     p[i] -= 2 * dp[i];
     dp[i] *= 0.9; 
    }
    
    
  }
    Kp = p[0];
  	Kd = p[1];
  	Ki = p[2];
    std::cout << Kp << std::endl;
  }
  
  
}
