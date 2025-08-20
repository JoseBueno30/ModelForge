package bankaccount;

public class Person{

	private Integer age;
	private String name;
	private Employee employee;

	// General constraints
	// salary > 0

	public Person(Integer age, String name) {
		this.setAge(age);
		this.setName(name);
	}

	private Integer getAge() {
		return this.age;
	}

	private void setAge(Integer age) {
				this.age = age;
	}

	public String getName() {
		return this.name;
	}

	public void setName(String name) {
				this.name = name;
	}

	public Employee getEmployee() {
		return this.employee;
	}

	public void setEmployee(Employee employee) {
		this.employee = employee;
	}

}
