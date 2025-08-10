package bankaccount;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Employee{

	private Integer salary;
	private Bank bank;
	private List<Person> employees;

	public Employee(Integer salary, Bank bank, Person employees, Person employees2, Person employees3, Person employees4, Person employees5, Person employees6) {
		this.setSalary(salary);
		this.setBank(bank);
		this.employees = new ArrayList<Person>();
			this.addEmployee(employees);
			this.addEmployee(employees2);
			this.addEmployee(employees3);
			this.addEmployee(employees4);
			this.addEmployee(employees5);
			this.addEmployee(employees6);
	}

	public Integer getSalary() {
		return this.salary;
	}

	public void setSalary(Integer salary) {
		this.salary = salary;
	}

	public Bank getBank() {
		return this.bank;
	}

	public void setBank(Bank bank) {
		if (this.bank != null) {
			this.bank.removeEmployee(this);
		}
		this.bank = bank;
		bank.addEmployee(this);
	}

	public List<Person> getEmployees() {
		return Collections.unmodifiableList(this.employees);
	}

	public void addEmployee(Person element) {
		this.employees.add(element);
		element.setEmployee(this);
	}

	public void removeEmployee(Person element) {
		if (this.employees.size() <= 6) {
			throw new IllegalStateException("Cannot remove element: minimum multiplicity of 6 would be violated.");
		}
		this.employees.remove(element);
		element.setEmployee(null);
	}

}
