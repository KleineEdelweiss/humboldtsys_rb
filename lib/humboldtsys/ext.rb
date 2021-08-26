# lib/humboldtsys/ext.rb

##
# Load the SysCore module or abort
begin
  # If installed, try to include the binary
  require "syscore.so"
rescue LoadError
  # Otherwise, include the Rake-compiled local version
  require_relative "../syscore/syscore"
rescue LoadError
  # If neither is found, abort
  abort("::FATAL:: Cannot load required SysCore extension -- try reinstalling")
end # End SysCore loader