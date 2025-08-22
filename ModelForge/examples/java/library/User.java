package library;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class User{

	private String dni;
	private String mail;
	private String name;
	private Integer tel;
	private List<Loan> loan;

	// General constraints
	// size() <= 1

	public User(String dni, String mail, String name, Integer tel) {
		this.setDni(dni);
		this.setMail(mail);
		this.setName(name);
		this.setTel(tel);
		this.loan = new ArrayList<Loan>();
	}

	public String getDni() {
		return this.dni;
	}

	public void setDni(String dni) {
				this.dni = dni;
	}

	public String getMail() {
		return this.mail;
	}

	public void setMail(String mail) {
				this.mail = mail;
	}

	public String getName() {
		return this.name;
	}

	public void setName(String name) {
				this.name = name;
	}

	public Integer getTel() {
		return this.tel;
	}

	public void setTel(Integer tel) {
				this.tel = tel;
	}

	public List<Loan> getLoan() {
		return Collections.unmodifiableList(this.loan);
	}

	public void addLoan(Loan element) {
		this.loan.add(element);
	}

	public void removeLoan(Loan element) {
		this.loan.remove(element);
	}

}
