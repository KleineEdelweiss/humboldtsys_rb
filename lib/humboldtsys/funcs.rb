# lib/humboldtsys/funcs.rb

# Require Extensions
require_relative "../share/other/other"

# This module contains generic functions that
# may be used for any purpose with a Linux system
module Funcs
  # Return the user's ID
  def self.uid() Other.uid end
  
  # Check if the user is `root`
  def self.root?() Other.root end
  
  # Check if the user is a member of at least
  # one of the group arguments.
  # 
  # This works because, if the input group subtracts
  # the output of the `groups` command (split into 
  # individual group names), then the length of the
  # input set is going to be, at most, equal.
  # 
  # If it is equal, that means nothing was removed from
  # the input set, so they are not a member of the input
  # groups. If the length is less, then that means one of
  # their groups has been removed from the input groups.
  def self.member?(groups)
    (groups - `groups`.strip.split).length < groups.length
  end # End member
  
  # Locate a file or directory,
  # and return a hash of the path and
  # whether it exists -- just an abstraction
  # method -- it returns the original path,
  # as well as whether or not it exists.
  def self.locate(path)
    {path: path, exists: File.exist?(path)}
  end # End locate
  
  # Abstract Command class that stores a command,
  # whatever arguments should be passed (by default),
  # and whatever groups can run it.
  class Command
    attr_reader :command, :args, :gnuargs
    # Constructor
    def initialize
      @command = ''
      @args = []
      @gnuagrs = []
    end # End constructor
    
    # Builds the command
    def build(command=@command, args=@args, gnuargs=@gnuargs)
      @command, @args, @gnuargs = command, args, gnuargs
    end # End build
    
    # Attempt to execute the command.
    # If the command exists and can be run
    # by the user, return the output. Otherwise,
    # return false.
    # 
    # This is an abstraction to avoid errors for files
    # that are not available on the system, and it can
    # be used generically or with the built-in checks.
    def run(args=@args, gnuargs=@gnuargs)
      argstring = (args.length > 0 ? "-#{args.join}" : "").strip
      gnuagrstring = gnuargs.collect { |garg| "--#{garg}" } .join(" ").strip
      cmdstring = "#{command} #{argstring} #{gnuagrstring}"
      begin
        `#{cmdstring}`
      rescue Errno::EACCES
        puts "User does not have permission to perform operation"
      rescue Errno::ENOENT
        puts "File or command not found"
      rescue => error
        puts error.message
      end
    end # End run
    alias :exec :run
    alias :execute :run
  end # End Commands class
end # End Funcs module