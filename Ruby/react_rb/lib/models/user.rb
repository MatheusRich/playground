# frozen_string_literal: true

class User
  attr_reader :name, :birthday

  def initialize(name, birthday)
    @name = name
    @birthday = birthday
  end
end
