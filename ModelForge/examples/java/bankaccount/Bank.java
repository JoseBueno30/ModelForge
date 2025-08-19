package bankaccount;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class Bank{

	private Set<Integer> test;
	private List<Employee> employee;

	public Bank() {
		this.test = new HashSet<>();
		this.employee = new ArrayList<Employee>();
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

	public List<Employee> getEmployee() {
		return Collections.unmodifiableList(this.employee);
	}

	public void addEmployee(Employee element) {
		this.employee.add(element);
	}

	public void removeEmployee(Employee element) {
		this.employee.remove(element);
	}

}
