require 'forwardable'

class Class
  def |(other)
    SumType.new(self, other)
  end
end

class SumType
  extend Forwardable
  attr_accessor :left, :right

  def_delegators :types, :to_s
  def_delegators :types, :inspect

  def initialize(left, right)
    @left = left
    @right = right
  end

  def |(other)
    SumType.new([@left, @right], other)
  end

  def types
    [left, right].flatten.uniq
  end

  def is_a?(other)
    types.include? other
  end
end

pp Integer | String
pp Integer | String | NilClass

maybe_string = (String | NilClass)
pp maybe_string.is_a? String
