import re

"""
Starting code for post processing

Things which might need to be processed:

- figures
- tables 
- page numbers
- headings
- bullets
"""


def postprocess(text):
    """Example function for figures only"""

    # Detect figures
    figures = re.finditer(r"(figure|fig|table)( ?)(.*)\.$", text, flags=re.IGNORECASE|re.DOTALL)
    # TODO : decide what to do with the detected figures

    # Detect bullets - all will be replaced by "*" bullet
    text = text.replace('/[#•»>‣◦⁃⁌⁍∙*]/gi', '*')

    return text