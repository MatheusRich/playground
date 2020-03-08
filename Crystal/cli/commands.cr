class Commands
  private THE_BEATLES = [
    "John Lennon",
    "Paul McCartney",
    "George Harrison",
    "Ringo Starr",
  ]

  WITH_ERROR = -1

  def initialize
    @options = {
      :should_shout       => false,
      :strawberry_mode_on => false,
    }
  end

  def version
    version = File.read("VERSION")
    puts "The Beatles CLI #{version}"
  end

  def help(parser : OptionParser)
    puts parser
  end

  def twist
    @options[:should_shout] = true
  end

  def strawberry
    @options[:strawberry_mode_on] = true
  end

  def default
    the_beatles
  end

  def hello(person)
    return if person.empty?

    say_hello(to: person)
  end

  def random_hello
    say_hello(to: THE_BEATLES.sample)
  end

  def missing_option(option_flag, parser)
    STDERR.puts "ERROR: #{option_flag} is missing something."
    STDERR.puts ""
    STDERR.puts parser
    exit(WITH_ERROR)
  end

  def invalid_option(option_flag, parser)
    STDERR.puts "ERROR: #{option_flag} is not a valid option."
    STDERR.puts ""
    STDERR.puts parser
    exit(WITH_ERROR)
  end

  private def the_beatles
    puts "Strawberry fields forever mode ON\n\n" if strawberry_mode_on?

    puts "Group members:"
    puts "=============="

    THE_BEATLES.each do |member|
      present_member(member)
    end
    puts ""
  end

  private def say_hello(to, from = THE_BEATLES.sample)
    puts "You say goodbye, and #{from} says hello to #{to}!"
  end

  private def present_member(member_name)
    puts "#{separator} #{formatted_name(member_name)}"
  end

  private def separator
    strawberry_mode_on? ? "🍓" : "-"
  end

  private def formatted_name(member_name)
    should_shout? ? member_name.upcase : member_name
  end

  private def should_shout?
    @options[:should_shout]
  end

  private def strawberry_mode_on?
    @options[:strawberry_mode_on]
  end
end
