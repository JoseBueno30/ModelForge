package bankaccount;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class Bank{

	private Set<Integer> test;
	private List<Person> employees;

	public Bank() {
		this.test = new HashSet<>();
		this.employees = new ArrayList<Person>();
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

	public List<Person> getEmployees() {
		return Collections.unmodifiableList(this.employees);
	}

	public void setEmployees(List<Person> employees) {
		this.employees = new ArrayList<Person>(employees);
	}

	public void addEmployee(Person element) {
		this.employees.add(element);
	}

	public void removeEmployee(Person element) {
		this.employees.remove(element);
	}

}
