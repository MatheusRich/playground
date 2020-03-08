require "option_parser"

the_beatles = [
  "John Lennon",
  "Paul McCartney",
  "George Harrison",
  "Ringo Starr"
]
shout = false

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
end

members = the_beatles
members = the_beatles.map &.upcase if shout

puts "Group members:"
puts "=============="

members.each do |member|
  puts member
end
