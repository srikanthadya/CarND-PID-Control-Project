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
   * Initialize PID coefficients (and errors, if needed)
   */
  this -> Kp = Kp_;
  this -> Ki = Ki_;
  this -> Kd = Kd_;
  
  this -> p_error = 0;
  this -> d_error = 0;
  this -> i_error = 0;
  this -> prev_err = 0;
  this -> best_err = 1000000;
  
  dp_p = Kp/100.;
  dp_d = Kd/100.0;
  dp_i = Ki/100.0;
  
  change = true;
  param = 0;
  
  

}

void PID::UpdateError(double cte) {
  /**
   * Update PID errors based on cte.
   */
  
  p_error = cte;
  d_error = p_error - prev_err;
  prev_err = cte;
  i_error += prev_err;
  
  counter +=1;
}

double PID::TotalError(double cte) {
  /**
   * Calculate and return the total error
   */
  
  total_error += (cte*cte);
  Twidel();
  
  return (Kp*p_error + Kd*d_error + Ki* i_error);  // TODO: Add your total error calc here!
}

void PID::Twidel(){
  
  
  
  current_err = total_error;

  //total_error = 0;
  double sum = 0;
  
  sum = dp_p + dp_d + dp_i;
  
  //if (counter > 10 ){
    
    //Kp += dp_p;
    //counter = 0;
    
    if (current_err < best_err){
      
      best_err = current_err;
      
      if (param == 0){
        dp_p *=1.1;
      }
      else if (param == 1){
        dp_d *=1.1;
      }
      else{
        dp_i *=1.1;
      }
      
      param = (param+1)%3;
      change = true;
    }
    else { 
      
      if (change == true){
        change = false;
      }
      
      else {
        
        if (param ==0){
          Kp += dp_p;
          dp_p *= 0.9;
        }
        
        else if (param ==1){
          Kd += dp_d;
          dp_d *= 0.9;
        }
        
        else {
          Ki += dp_i;
          dp_i *= 0.9;
        }
        
        param = (param+1)%3;
        change = true;
      }
      
    }
    if (param ==0){
      if (change == true){
        Kp += dp_p;
      }
      else{
        std::cout << "Kp " << std::endl;
        Kp -= 2*dp_p;
      }      
    }
    if (param ==1){
      if (change == true){
        Kd += dp_d;
      }
      else{
        std::cout << "Kd " << std::endl;
        Kd -= 2*dp_d;
      }      
    }
    if (param ==2){
      if (change == true){
        Ki += dp_i;
      }
      else{
        std::cout << "Ki " << std::endl;
        Ki -= 2*dp_i;
      }      
    }
  std::cout << Kp << " " << Ki << " " << Kd << std::endl;
  }
  
  
//}
