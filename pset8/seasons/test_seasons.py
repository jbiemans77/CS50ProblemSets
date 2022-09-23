from seasons import ValidateDateFormat
from seasons import GetSongOutput

def test_GetSongOutput_normal():
    assert GetSongOutput("1999-12-25") == "Eleven million, nine hundred forty-seven thousand, six hundred eighty minutes"
    assert GetSongOutput("1900-01-01") == "Sixty-four million, five hundred thirty-two thousand, one hundred sixty minutes"


def test_ValidateDateFormat_normal():
    assert ValidateDateFormat("1999-12-25") == True
    assert ValidateDateFormat("1900-01-01") == True
    assert ValidateDateFormat("June 1st, 1900") == False