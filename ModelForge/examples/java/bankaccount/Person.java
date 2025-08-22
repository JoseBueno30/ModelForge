package bankaccount;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Person{

	private Integer age;
	private String name;
	private List<Account> accounts;
	private Employee employee;
	private List<Account> usedAccounts;

	public Person(Integer age, String name) {
		this.setAge(age);
		this.setName(name);
		this.accounts = new ArrayList<Account>();
		this.usedAccounts = new ArrayList<Account>();
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

	public List<Account> getAccounts() {
		return Collections.unmodifiableList(this.accounts);
	}

	public void addAccount(Account element) {
		this.accounts.add(element);
	}

	public void removeAccount(Account element) {
		this.accounts.remove(element);
	}

	public Employee getEmployee() {
		return this.employee;
	}

	public void setEmployee(Employee employee) {
		this.employee = employee;
	}

	public List<Account> getUsedAccounts() {
		return Collections.unmodifiableList(this.usedAccounts);
	}

	public void addUsedAccount(Account element) {
		this.usedAccounts.add(element);
	}

	public void removeUsedAccount(Account element) {
		this.usedAccounts.remove(element);
	}

}
