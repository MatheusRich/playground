require 'forwardable'

class Class
  def |(other)
    SumType.new(self, other)
  end
end

class SumType
  extend Forwardable
  attr_accessor :left, :right

  def_delegators :inspect, :to_s

  def initialize(left, right)
    @left = left
    @right = right
  end

  def |(other)
    SumType.new([@left, @right], other)
  end

  def ==(other)
    value = other.is_a?(SumType) ? other.types : other

    types.sort_by(&:to_s) == [value].flatten(1).uniq.sort_by(&:to_s)
  end

  def types
    [left, right].flatten.uniq
  end

  def include?(other)
    types.include? other
  end

  def inspect
    "<#{types.join(' | ')}>"
  end
end

pp Integer | String | NilClass

maybe_string = (String | NilClass)
another_maybe_string = (String | NilClass)

pp maybe_string.include? String
pp maybe_string.include? another_maybe_string
pp maybe_string == maybe_string
pp maybe_string == String
