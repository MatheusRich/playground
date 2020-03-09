require "option_parser"
require "./commands"

commands = Commands.new

OptionParser.parse do |parser|
  parser.banner = "Welcome to The Beatles App!"

  parser.on "-v", "--version", "Show version" do
    commands.version
    exit
  end

  parser.on "-h", "--help", "Show help" do
    commands.help(parser)
    exit
  end

  parser.on "-t", "--twist", "Twist and SHOUT" do
    commands.twist
  end

  parser.on "-s", "--strawberry", "Strawberry fields forever mode ON" do
    commands.strawberry
  end

  parser.on "-g NAME", "--goodbye_hello=NAME", "Say hello to whoever you want" do |name|
    commands.hello(to: name)
    exit
  end

  parser.on "-r", "--random_goodbye_hello", "Say hello to one random member" do
    commands.random_hello
    exit
  end

  parser.missing_option do |option_flag|
    commands.missing_option(option_flag, parser)
  end

  parser.invalid_option do |option_flag|
    commands.invalid_option(option_flag, parser)
  end
end

commands.default
