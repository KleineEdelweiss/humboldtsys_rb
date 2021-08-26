# lib/humboldtsys/templates/currently.rb

##
# Objects that include this module must supply
# a way to adjust to a current version of
# the object's data -- namely, :specific_update
# 
# This method does not need to return a specific
# type or format of data, but the data should be current,
# as the update method sets the reader.
module Currently
  # Data to be stored
  attr_reader :current
  
  ##
  # This method returns the current state of the
  # data stored in the object.
  def stat() current end
  
  ##
  # Abstract update method, assigns value to :current,
  # returns :stat.
  # 
  # :update and :stat are different, in the likely
  # event that an includer does not intend to run
  # process-heavy update cycles every time the object
  # is statted -- for example, returning a cached value
  # in between updates on a timer.
  def update
    @current = specific_update
    true
  end # End update method
  
  ##
  # This method needs to be overridden, so that
  # each type including it can be updated correctly
  def specific_update
    STDERR.puts "::WARNING:: Including classes must implement #{__method__}"
    nil
  end # End specific update method
end # End Currently module