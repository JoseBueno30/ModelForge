package family;

public class Assoc{

	private Integer age;
	private Person persona1;
	private Test prueba1;

	public Assoc(Integer age, Person persona1, Test prueba1) {
		this.setAge(age);
		this.setPersona1(persona1);
		this.setPrueba1(prueba1);
	}

	public Integer getAge() {
		return this.age;
	}

	public void setAge(Integer age) {
		//self.age > 0
		this.age = age;
	}

	public Person getPersona1() {
		return this.persona1;
	}

	public void setPersona1(Person persona1) {
		if (persona1 == null) {
			throw new IllegalArgumentException("persona1 must not be null.");
		}
		if (this.persona1 != null) {
			this.persona1.setAssoc(null);
		}
		this.persona1 = persona1;
		persona1.setAssoc(this);
	}

	public Test getPrueba1() {
		return this.prueba1;
	}

	public void setPrueba1(Test prueba1) {
		if (prueba1 == null) {
			throw new IllegalArgumentException("prueba1 must not be null.");
		}
		if (this.prueba1 != null) {
			this.prueba1.setAssoc(null);
		}
		this.prueba1 = prueba1;
		prueba1.setAssoc(this);
	}

}
