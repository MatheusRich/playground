# frozen_string_literal: true

class Object
  def and_then(arg)
    arg.call(self)
  end
end

phrase = 'my string is cool'
scream = ->(str) { str.upcase }
capitalize = ->(str) { str.capitalize }
split_by_space = ->(str) { str.split }
add_emotion = ->(array) { array.last.upcase!; array }
join = ->(array) { array.join(' ') }

# Current syntax
pp phrase.then(&scream)
         .then(&capitalize)
         .then(&split_by_space)
         .then(&add_emotion)
         .then(&join)

# Syntax sugar: Removes the '&'
pp phrase.and_then(scream)
         .and_then(capitalize)
         .and_then(split_by_space)
         .and_then(add_emotion)
         .and_then(join)

# Current syntax
pp phrase.then(&scream >> capitalize >> split_by_space >> add_emotion >> join)

# Current syntax v2
pp (scream >> capitalize >> split_by_space >> add_emotion >> join).call(phrase)

# Syntax sugar: Removes the '&'. Ideally this would be a token like |>
pp phrase.and_then(scream >> capitalize >> split_by_space >> add_emotion >> join)
