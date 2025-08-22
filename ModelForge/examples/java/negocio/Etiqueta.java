package negocio;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Etiqueta extends Contrato{

	private Integer cantidad;
	private Integer precio;
	private List<Empresa> empresa_propietaria;
	private List<Producto> producto;

	public Etiqueta(String puesto, Integer salario, Integer cantidad, Integer precio) {
		super(puesto, salario);
		this.setCantidad(cantidad);
		this.setPrecio(precio);
		this.empresa_propietaria = new ArrayList<Empresa>();
		this.producto = new ArrayList<Producto>();
	}

	public Integer getCantidad() {
		return this.cantidad;
	}

	public void setCantidad(Integer cantidad) {
				this.cantidad = cantidad;
	}

	public Integer getPrecio() {
		return this.precio;
	}

	public void setPrecio(Integer precio) {
				this.precio = precio;
	}

	public List<Empresa> getEmpresa_propietaria() {
		return Collections.unmodifiableList(this.empresa_propietaria);
	}

	public void addEmpresa_propietaria(Empresa element) {
		this.empresa_propietaria.add(element);
		element.addEtiqueta(this);
	}

	public void removeEmpresa_propietaria(Empresa element) {
		this.empresa_propietaria.remove(element);
		element.removeEtiqueta(this);
;
	}

	public List<Producto> getProducto() {
		return Collections.unmodifiableList(this.producto);
	}

	public void addProducto(Producto element) {
		this.producto.add(element);
		element.addEtiqueta(this);
	}

	public void removeProducto(Producto element) {
		this.producto.remove(element);
		element.removeEtiqueta(this);
;
	}

}
