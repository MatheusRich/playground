# frozen_string_literal: true

def page
  my_header + yield + my_footer
end

private

BaseStyle = Stylesheet.new({
  my_body: {
    margin: 0
  },
  my_header: {
    box_shadow: '0 3px 4px rgba(0, 0, 0, 0.25)',
    width: '100%',
    padding: '5px 20px',
    margin_bottom: '10px'
  },
  my_title: {
    font_size: '25px'
  }
})

def my_header
  div style: BaseStyle.my_header do
    h1 'My App', style: BaseStyle.my_title
  end
end

def my_footer
  ''
end