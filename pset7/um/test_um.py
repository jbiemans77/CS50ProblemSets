from um import count

def test_count_in_words():
    assert count("unbrella") == 0
    assert count("drum") == 0
    assert count("clumsy") == 0


def test_count_only_um():
    assert count("um") == 1


def test_count_case_insensitive():
    assert count("um") == 1
    assert count("uM") == 1
    assert count("Um") == 1
    assert count("UM") == 1

def test_count_umm():
    assert count("umm") == 0
    assert count("um umm um") == 2


def test_whole_sentences():
    assert count("The um quick um brown umm, um, fox jumps over the um, lazy umm umbrella!") == 4