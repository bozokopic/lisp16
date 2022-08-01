from pathlib import Path

root_path = Path(__file__).parent.parent.resolve()

extensions = ['sphinx.ext.todo']

version = (root_path / 'VERSION').read_text(encoding='utf-8').strip()
project = 'lisp16'
copyright = '2022, Bozo Kopic'
master_doc = 'index'

html_theme = 'furo'
html_static_path = ['static']
html_css_files = ['custom.css']
html_use_index = False
html_show_sourcelink = False
html_show_sphinx = False
html_sidebars = {'**': ["sidebar/brand.html",
                        "sidebar/scroll-start.html",
                        "sidebar/navigation.html",
                        "sidebar/scroll-end.html"]}

todo_include_todos = True
