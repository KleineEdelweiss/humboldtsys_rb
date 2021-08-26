# lib/humboldtsys/procfs.rb

require_relative "constants"

# This module will handle parsing of data in the
# /proc/ virtual filesystem.
module ProcFS
  # Count the total number of processes running
  # on the host system
  def self.count
    list.length
  end # End process count
  
  # List the numbers of processes running
  def self.list
    Dir.entries("/proc").reject {|e| !e.match?(/^\d+$/)}
  end # End process list
end # End ProcFS module