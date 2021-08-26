# lib/humboldtsys/templates/windowable.rb

##
# Inclusion module to support basic operations on
# an object type that should be able to support
# a windowed reference
module Windowable
  # Gets the dequeue used in the window
  def get_dequeue() @dequeue end
  alias :raw :get_dequeue
  
  # Count of items currently windowed
  def count() get_dequeue.count end
  
  # Raw maximum / total available of usable units
  def sum() get_dequeue.sum end
  
  # Current usage of the object's available units
  def average() sum / count.to_f end
  
  # Add a unit to the end of the dequeue
  def insert(item) get_dequeue.push(item) end
  alias :push :insert
  
  # Remove a unit from the start of the dequeue
  def remove() get_dequeue.shift end
  alias :pop :remove
  
  ##
  # Overrideable methods
  
  # Set the default dequeue -- overrideable
  def local_set_dequeue(dequeue) raise NotImplementedError end
end # End Calculable module