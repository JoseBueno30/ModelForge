package bankaccount;
public class Bank{

	private Set<int> test;

public Bank() {
	}

	public Set<int> getTest() {
		return this.test;
	}

	public void setTest(Set<int> test) {
		this.test = test;
	}

	public void addTest(int element) {
		this.test.add(element);
	}

	public void removeTest(int element) {
		this.test.remove(element);
	}

}
