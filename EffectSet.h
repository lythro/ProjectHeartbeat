#pragma once
/**
 * Always contains a fixed number of elements.
 * These must implement a method 'void getRGB( .. )'
 * (see: Effect), as to allow the EffectSet to be
 * evaluated as a whole.
 */
template<class T>
class EffectSet {
	public:
		EffectSet( int size ) {
			m_size = size;
			m_oldest = 0;
			m_elements = new T[size];
			m_numLEDs = 60;
			for (int i = 0; i < m_size; i++) {
				m_elements[i].setNumLEDs( m_numLEDs );
			}
		}

		~EffectSet() {
			delete[] m_elements;
		}


		/**
		 * Creates a new instance of type T and 
		 * overwrites the oldest entry.
		 * \return A reference to the newest entry.
		 */
		T& create() {
			m_elements[m_oldest] = T();
			m_elements[m_oldest].setNumLEDs( m_numLEDs );
			
			m_oldest++;
			if (m_oldest >= m_size) m_oldest = 0;

			return m_elements[m_oldest];
		}


		/**
		 * Set the number of LEDs, will be set for every
		 * effect in the set, too.
		 */
		void setNumLEDs( unsigned char num ) {
			m_numLEDs = num;
			for (int i = 0; i < m_size; i++) {
				m_elements[i].setNumLEDs( num );
			}
		}

		/**
		 * Evaluates the whole EffectSet for a given LED.
		 */
		void getRGB( unsigned char id, unsigned char* r,
										unsigned char* g,
										unsigned char* b ) const {

			unsigned char tr, tg, tb; // temp to eval on
			int br, bg, bb; // buffer to sum everything up
			br = bg = bb = 0;
			for (int i = 0; i < m_size; i++) {
				m_elements[i].getRGB( id, &tr, &tg, &tb );
				br += tr;
				bg += tg;
				bb += tb;
			}
			// cap at 255
			tr = (br > 255 ? 255 : br);
			tg = (bg > 255 ? 255 : bg);
			tb = (bb > 255 ? 255 : bb);

			// output
			*r = tr;
			*g = tg;
			*b = tb;
		}

		/**
		 * Updates all Effects. If one isDone(), create a new one.
		 */
		void next() {
			for (int i = 0; i < m_size; i++) {
				m_elements[i].next();
				if (m_elements[i].isDone()) {
					m_elements[i] = T();
					m_elements[i].setNumLEDs( m_numLEDs );
				}
			}
		}


		/**
		 * \return number of elements
		 */
		int size() const { return m_size; }


		/**
		 * \return reference to the i'th element
		 */
		T& operator[] ( int i ) {
			return m_elements[i];
		}

		/**
		 * Change the size of the set, by creating new elements,
		 * or removing the *newest*. (This is used for the comethail,
		 * in which the newest comets will start offscreen!)
		 */
		void resize( int size ) {
			if (m_size == size) return;

			// new array of elements
			T* newElements = new T[size];
			for (int i = 0; i < size; i++) {
				newElements[i].setNumLEDs( m_numLEDs );
			}

			// if our size was 0, nothing to copy, just
			// return with the new elements..
			if (m_size == 0) return;

			// else, copy our elements into the new list,
			// oldest first
			for (int i = 0; i < size && i < m_size; i++) {
				int index = m_oldest + i;
				if (index >= m_size) index -= m_size;
				newElements[i] = m_elements[index];
			}

			// cleanup
			delete[] m_elements;
			m_elements = newElements;
			m_size = size;
			m_oldest = 0;
		}

	private:
		int m_numLEDs;
		int m_size;
		int m_oldest;
		T* m_elements;
};
