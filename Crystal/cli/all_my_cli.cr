require "option_parser"

THE_BEATLES = [
  "John Lennon",
  "Paul McCartney",
  "George Harrison",
  "Ringo Starr"
]
WITH_ERROR = -1

person = ""
shout = false
strawberry_mode_on = false


OptionParser.parse do |parser|
  parser.banner = "Welcome to The Beatles App!"

  parser.on "-v", "--version", "Show version" do
    puts "version 1.0"
    exit
  end
  parser.on "-h", "--help", "Show help" do
    puts parser
    exit
  end
  parser.on "-t", "--twist", "Twist and SHOUT" do
    shout = true
  end
  parser.on "-g NAME", "--goodbye_hello=NAME", "Say hello to whoever you want" do |name|
    person = name
  end
  parser.on "-r", "--random_goodbye_hello", "Say hello to one random member" do
    person = THE_BEATLES.sample
  end
  parser.on "-s", "--strawberry", "Strawberry fields forever mode ON" do
    strawberry_mode_on = true
  end
  parser.missing_option  do |option_flag|
    STDERR.puts "ERROR: #{option_flag} is missing something."
    STDERR.puts ""
    STDERR.puts parser
    exit(WITH_ERROR)
  end
  parser.invalid_option  do |option_flag|
    STDERR.puts "ERROR: #{option_flag} is not a valid option."
    STDERR.puts ""
    STDERR.puts parser
    exit(WITH_ERROR)
  end
end


members = THE_BEATLES
members = THE_BEATLES.map &.upcase if shout

puts "Strawberry fields forever mode ON\n\n" if strawberry_mode_on


puts "Group members:"
puts "=============="

members.each do |member|
  puts "#{strawberry_mode_on ? "🍓" : "-"} #{member}"
end
puts ""


exit if person.empty?

puts "You say goodbye, and #{THE_BEATLES.sample} says hello to #{person}!"
