import coverage.annotate

code = """
int main() {
	if(true) {
		return 1;
	}
	else {
		return 2;
	}
}
"""

def test_me():

	coverage.annotate.annotate(code)
	assert True
