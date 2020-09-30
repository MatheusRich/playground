# frozen_string_literal: true

def bio(name:, birthday:)
  div style: Styles.box do
    div style: Styles.row do
      strong 'Name: '
      span name
    end
    div style: (Styles.row + Styles.even_row) do
      strong 'Age: '
      span age(birthday)
    end
  end
end

private

def age(birthday)
  today = Time.now
  today.year - birthday.year - (today.month > birthday.month || (today.month == birthday.month && today.day >= birthday.day) ? 0 : 1)
end

Styles = Stylesheet.new({
  box: {
    border: '1px solid black',
    width: 'fit-content'
  },
  row: { padding: '10px' },
  even_row: { background_color: 'lightgray' }
})
