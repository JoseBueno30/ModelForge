package bankaccount;
import java.util.HashSet;
import java.util.Set;

public class Bank{

	private Set<Integer> test;

	public Bank(Set<Integer> test) {
		this.setTest(test);
	}

	public Set<Integer> getTest() {
		return this.test;
	}

	public void setTest(Set<Integer> test) {
		this.test = test;
	}

	public void addTest(Integer element) {
		this.test.add(element);
	}

	public void removeTest(Integer element) {
		this.test.remove(element);
	}

}
