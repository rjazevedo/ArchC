/**
 * @file   ac_module.cpp
 * @author Thiago Massariolli Sigrist
 * @date   Thu May 12 10:29:52 2005
 * 
 * @brief  Implementation for ArchC abstract module class.
 * 
 * 
 */

//////////////////////////////////////////////////////////////////////////////

// Standard includes
#include <iostream>

// SystemC includes

// ArchC includes
#include "ac_module.H"

//////////////////////////////////////////////////////////////////////////////

// 'using' declarations

//////////////////////////////////////////////////////////////////////////////

/// The next module ID.
unsigned ac_module::next_mod_id = 0;

/// Number of currently running modules.
unsigned ac_module::running_mods = 0;

/// Standard constructor.
ac_module::ac_module() : sc_module(sc_gen_unique_name("ac_module")),
			 mod_id(next_mod_id++),
			 ac_stop_flag(0),
			 ac_exit_status(0) {}

/// Named constructor.
ac_module::ac_module(sc_module_name nm) : sc_module(nm),
					  mod_id(next_mod_id++),
					  ac_stop_flag(0),
					  ac_exit_status(0) {}

/// Public method that registers module as a running module.
void ac_module::set_running() {
  running_mods++;
}

/// Public method that unregisters module (ie, it's no longer running).
void ac_module::set_stopped() {
  if (--running_mods == 0) {
    dup2(2, 1); //any output to stdout is redirected for stderr (ex. SystemC stop message)
    sc_stop();
  }
}