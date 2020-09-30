# frozen_string_literal: true

require 'sinatra'
require 'sinatra/reloader'

require_relative 'lib/views'
require_relative 'lib/helpers'

require_all 'models'
require_all 'components'

user = User.new('Matheus', Time.parse('1997-12-08'))

get '/' do
  bio(name: user.name, birthday: user.birthday)
end
