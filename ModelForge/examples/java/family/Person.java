package family;

public class Person{

	private Integer age;
	private String name;
	private String surname1;
	private String surname2;
	private Assoc assoc;

	// General constraints
	// if self.father <> null and self.mother <> null then self.father.age > self.age and self.mother.age > self.age else true endif
	// if self.father <> null and self.mother <> null then self.father.surname1 = self.surname1 and self.mother.surname1 = self.surname2 else true endif
	// self.brother2 -> forAll(father=self.fatherormother=self.mother)
	// self.cousin2 -> forAll(p:Person | self.uncle -> exists(p2:Person | self.uncle -> p2 = p.father or p.father.p2 = p.mother))
	// self.uncle -> forAll(p:Person | p.brother2 -> exists(p2:Person | p.brother2 -> p2 = self.father or self.father.p2 = self.mother) or p.brother1 -> exists(p2:Person | p.brother1 -> p2 = self.father or self.father.p2 = self.mother))

	public Person(Integer age, String name, String surname1, String surname2) {
		this.setAge(age);
		this.setName(name);
		this.setSurname1(surname1);
		this.setSurname2(surname2);
	}

	public Integer getAge() {
		return this.age;
	}

	public void setAge(Integer age) {
		//self.age > 0
		this.age = age;
	}

	public String getName() {
		return this.name;
	}

	public void setName(String name) {
				this.name = name;
	}

	public String getSurname1() {
		return this.surname1;
	}

	public void setSurname1(String surname1) {
				this.surname1 = surname1;
	}

	public String getSurname2() {
		return this.surname2;
	}

	public void setSurname2(String surname2) {
				this.surname2 = surname2;
	}

	public Assoc getAssoc() {
		return this.assoc;
	}

	public void setAssoc(Assoc assoc) {
		if (assoc == null) {
			throw new IllegalArgumentException("assoc must not be null.");
		}
		this.assoc = assoc;
	}

	public Integer cumplirAnios(Integer anios){
		// Pre Condition <EdadValida>: self.age >= 0
		// Pre Condition <EdadValidad>: self.age >= -1
		/*
	
		*/
		// Post Condition <EdadIncrementada>: self.age.result = self.age + 1 and self.age = self.age + 1
	}
	public Boolean esMayorDeEdad(){
		/*
	
		*/
	}
}
