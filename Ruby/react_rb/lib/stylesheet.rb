# frozen_string_literal: true

class Stylesheet
  def initialize(styles)
    @styles = styles
  end

  def parse_style(hash)
    final = ''

    hash.each do |(key, value)|
      style = key.to_s.gsub('_', '-') + ':' + value.to_s + ';'

      final += style
    end

    final
  end

  def method_missing(name, *args)
    style = @styles[name]
    return super unless style

    parse_style(style)
  end
end
