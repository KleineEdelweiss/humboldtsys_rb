# lib/humboldtsys/funcs/lspci.rb

require_relative "../funcs"

# This class performs some default operations of on the
# `lspci` command and generates a basic, parseable output.
module Lspci
  # Lspci class
  class Lspci < Funcs::Command
    # Specific constructor
    def initialize
      build(command='lspci', args=["D", "n", "n", "v", "v", "v", "k", "m", "m"], gnuargs=[])
    end # End specific constructor
    
    # Run, but now specific
    def run
      super.split(/^\s*$/).collect { |dev| device(dev.strip) }
    end # End specific run
    
    # Create a device from a set of fields
    def device(fields)
      fields.split("\n").collect do |line|
        line.split(/:\s*/, 2).then { |k,v| {k.downcase.strip.to_sym => v.strip } }
      end.reduce :update
    end # End device
  end # End Lspci class
end # End Lspci module