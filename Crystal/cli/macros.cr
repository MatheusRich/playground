macro define_option_property(*options)
  {% for option in options %}
    private def {{option.id}}?
      @options[:{{option}}]
    end
  {% end %}
end
