package family;

public class Test{

	private Boolean name;
	private Assoc assoc;

	public Test(Boolean name) {
		this.setName(name);
	}

	public Boolean getName() {
		return this.name;
	}

	public void setName(Boolean name) {
				this.name = name;
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

	public Person esMayorDeEdad(){
		/*
	
		*/
	}
}
