# lib/humboldtsys/external.rb

require_relative "funcs"

# This module will be used to check for the existence
# of certain programs that may be statted for particular
# system information.
module Extern
  # Progs is a class that will store all the information
  # about system programs that can be readily accessed
  class Progs
    attr_reader :programs
    
    # Constructor
    def initialize
      @programs = defaults
    end # end constructor
    
    # Check for the existence of
    # external programs, which certain
    # data and settings access may rely on.
    # 
    # Each program will be listed as whether
    # it requires root access or not.
    def defaults
      {
        :lspci => 'lspci -Dnnvvvkmm',
        :dmidecode => '',
      }
    end # End program checker
  end # End Progs class
end # End Extern module