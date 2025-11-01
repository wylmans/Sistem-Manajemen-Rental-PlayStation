# 🤝 Contributing to Rental PlayStation Management System

Terima kasih atas minat Anda untuk berkontribusi! Dokumen ini berisi panduan untuk berkontribusi pada project ini.

## 📋 Daftar Isi

- [Code of Conduct](#code-of-conduct)
- [Getting Started](#getting-started)
- [How to Contribute](#how-to-contribute)
- [Development Workflow](#development-workflow)
- [Coding Standards](#coding-standards)
- [Testing Guidelines](#testing-guidelines)
- [Documentation](#documentation)
- [Pull Request Process](#pull-request-process)
- [Community](#community)

---

## Code of Conduct

### Our Pledge

Kami berkomitmen untuk membuat project ini ramah dan inklusif untuk semua. Kami menghargai kontribusi dari siapa saja, tanpa memandang:

- Tingkat pengalaman
- Gender identity dan ekspresi
- Orientasi seksual
- Disabilitas
- Penampilan fisik
- Usia
- Ras, etnis, atau nasionalitas
- Agama atau kepercayaan

### Expected Behavior

- Gunakan bahasa yang ramah dan inklusif
- Hormati sudut pandang dan pengalaman berbeda
- Terima kritik konstruktif dengan baik
- Fokus pada yang terbaik untuk komunitas
- Tunjukkan empati kepada anggota komunitas lainnya

### Unacceptable Behavior

- Komentar yang menghina atau merendahkan
- Harassment dalam bentuk apapun
- Trolling atau komentar yang provokatif
- Publishing informasi pribadi orang lain
- Conduct yang tidak profesional

---

## Getting Started

### Prerequisites

Sebelum mulai berkontribusi, pastikan Anda memiliki:

- Git installed
- Qt 6.2+ installed
- C++ compiler (GCC 9+, Clang 10+, atau MSVC 2019+)
- CMake 3.16+
- Basic understanding of:
  - C++ and Qt Framework
  - SQL databases
  - Git workflow

### Setting Up Development Environment

1. **Fork the Repository**
   ```bash
   # Klik tombol "Fork" di GitHub
   # Clone your fork
   git clone https://github.com/YOUR_USERNAME/rental-playstation.git
   cd rental-playstation
   ```

2. **Add Upstream Remote**
   ```bash
   git remote add upstream https://github.com/ORIGINAL_OWNER/rental-playstation.git
   git fetch upstream
   ```

3. **Install Dependencies**
   ```bash
   # Ubuntu/Debian
   sudo apt install qt6-base-dev qt6-tools-dev cmake
   
   # macOS
   brew install qt@6 cmake
   
   # Windows: Install from Qt website
   ```

4. **Build the Project**
   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```

5. **Run Tests** (jika ada)
   ```bash
   ctest
   ```

---

## How to Contribute

### Types of Contributions

Kami menerima berbagai jenis kontribusi:

#### 🐛 Bug Reports

Jika menemukan bug:

1. **Search existing issues** - Pastikan bug belum dilaporkan
2. **Create new issue** dengan template bug report
3. **Include**:
   - Clear description
   - Steps to reproduce
   - Expected vs actual behavior
   - Screenshots (jika relevan)
   - Environment details (OS, Qt version, dll)

**Template:**
```markdown
**Bug Description**
Clear and concise description.

**To Reproduce**
1. Go to '...'
2. Click on '...'
3. See error

**Expected Behavior**
What you expected to happen.

**Screenshots**
If applicable.

**Environment:**
- OS: [e.g., Ubuntu 22.04]
- Qt Version: [e.g., 6.5.3]
- Compiler: [e.g., GCC 11.4]
```

#### ✨ Feature Requests

Untuk request fitur baru:

1. **Check existing requests** di Issues
2. **Create new issue** dengan template feature request
3. **Explain**:
   - Use case
   - Proposed solution
   - Alternatives considered

**Ideas for Features:**
- [ ] Member discount system
- [ ] Email/SMS notifications
- [ ] Dashboard with analytics
- [ ] Print receipt functionality
- [ ] Mobile responsive design
- [ ] Multi-language support
- [ ] User authentication & roles
- [ ] Revenue reports & charts
- [ ] Automatic reminder before session ends
- [ ] Loyalty points system

#### 📝 Documentation

Documentation improvements are always welcome:

- Fix typos
- Clarify confusing sections
- Add examples
- Translate to other languages
- Add diagrams or screenshots

#### 💻 Code Contributions

Code contributions can include:

- Bug fixes
- New features
- Performance improvements
- Code refactoring
- Test coverage improvements

---

## Development Workflow

### Branch Strategy

```
main (or master)
  ├── develop
  │   ├── feature/add-member-discount
  │   ├── feature/email-notification
  │   └── bugfix/calculate-bonus-error
  └── hotfix/critical-database-bug
```

**Branch Naming:**
- `feature/descriptive-name` - New features
- `bugfix/issue-description` - Bug fixes
- `hotfix/critical-issue` - Critical production fixes
- `docs/what-changed` - Documentation updates
- `refactor/component-name` - Code refactoring

### Development Steps

1. **Create Feature Branch**
   ```bash
   git checkout develop
   git pull upstream develop
   git checkout -b feature/your-feature-name
   ```

2. **Make Changes**
   - Write clean, readable code
   - Follow coding standards
   - Add comments for complex logic
   - Update documentation if needed

3. **Test Your Changes**
   ```bash
   # Build
   cmake --build build
   
   # Test manually
   ./build/bin/RentalManagementSystem
   
   # Run automated tests
   cd build && ctest
   ```

4. **Commit Changes**
   ```bash
   git add .
   git commit -m "Add: member discount calculation feature"
   ```

   **Commit Message Format:**
   ```
   Type: Brief description
   
   Longer description if needed.
   Explain what and why, not how.
   
   Fixes #123
   ```

   **Types:**
   - `Add`: New feature
   - `Fix`: Bug fix
   - `Update`: Update existing feature
   - `Refactor`: Code refactoring
   - `Docs`: Documentation changes
   - `Test`: Adding/updating tests
   - `Style`: Formatting, missing semicolons, etc.

5. **Push to Your Fork**
   ```bash
   git push origin feature/your-feature-name
   ```

6. **Create Pull Request**
   - Go to GitHub
   - Click "New Pull Request"
   - Fill in PR template
   - Wait for review

---

## Coding Standards

### C++ Style Guide

#### Naming Conventions

```cpp
// Classes: PascalCase
class DatabaseManager { };

// Functions: camelCase
void calculateNightBonus();

// Variables: camelCase
int totalHours;
QString customerName;

// Constants: UPPER_SNAKE_CASE
const int MAX_BONUS_HOURS = 10;

// Member variables: camelCase with 'm' prefix (optional)
private:
    int mCustomerId;
    QString mCustomerName;
```

#### Code Formatting

```cpp
// Use 4 spaces for indentation (no tabs)
if (condition) {
    doSomething();
}

// Braces on same line
void function() {
    // code
}

// Space after keywords
if (x > 0) {
    for (int i = 0; i < 10; ++i) {
        // code
    }
}

// No space before function parentheses
void myFunction(int param);

// Use nullptr instead of NULL
MyClass *ptr = nullptr;

// Use auto when type is obvious
auto value = someComplexFunction();

// But be explicit when unclear
QDateTime startTime = getStartTime();  // Better than auto
```

#### Comments

```cpp
// Single-line comment for brief explanations
int totalHours = 6;  // 6 hours rental

/**
 * Multi-line comment for functions
 * 
 * Calculate bonus hours for night rentals.
 * Night period is defined as 21:00 - 06:00.
 * 
 * @param startTime The rental start time
 * @param durationHours Total rental duration in hours
 * @return Bonus hours (1 hour per 3 hours at night)
 */
double calculateNightBonus(const QDateTime &startTime, int durationHours);

// TODO: Implement member discount calculation
// FIXME: Bonus calculation incorrect for multi-day rentals
// NOTE: This function is performance-critical
```

### Qt-Specific Guidelines

```cpp
// Use Qt types when appropriate
QString text;          // Not std::string
QList<int> numbers;    // Not std::vector<int>
QDateTime time;        // Not std::chrono

// Use Qt's signal-slot mechanism
connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClick);

// Use Qt's parent-child ownership
QWidget *widget = new QWidget(parent);  // parent will delete widget

// Prefer Qt algorithms
QList<int> numbers = {1, 2, 3, 4, 5};
int sum = std::accumulate(numbers.begin(), numbers.end(), 0);

// Use Qt's foreach when appropriate
foreach (const QString &name, nameList) {
    qDebug() << name;
}
```

### SQL Guidelines

```sql
-- Use uppercase for keywords
SELECT * FROM Sistem_rental WHERE Id_Customer = 'C001';

-- Use meaningful table/column names
CREATE TABLE Sistem_rental (  -- Good
    Id_Rental INTEGER,
    Nama_Customer VARCHAR(100)
);

-- NOT:
CREATE TABLE sr (  -- Bad: unclear abbreviation
    id INT,
    name VARCHAR(100)
);

-- Use prepared statements to prevent SQL injection
query.prepare("SELECT * FROM table WHERE id = :id");
query.bindValue(":id", customerId);
```

---

## Testing Guidelines

### Manual Testing Checklist

Before submitting PR, test:

- [ ] Database connection (SQLite, PostgreSQL, MySQL)
- [ ] Data loading dan display
- [ ] Filter functionality
- [ ] Bonus calculation accuracy
- [ ] Remaining time updates
- [ ] Status changes
- [ ] CSV export with all columns
- [ ] UI responsiveness
- [ ] Error handling

### Test Cases for Calculations

```cpp
// Test 1: Full night session
Start: 2024-11-01 22:00:00
Duration: 6 hours
Expected Bonus: 2.0 hours

// Test 2: Partial night
Start: 2024-11-01 20:00:00
Duration: 6 hours (4 hours at night)
Expected Bonus: 1.33 hours

// Test 3: Day session
Start: 2024-11-01 10:00:00
Duration: 5 hours
Expected Bonus: 0.0 hours

// Test 4: Remaining time positive
End: (current time + 2 hours)
Expected: ~2.0 hours

// Test 5: Remaining time negative (overtime)
End: (current time - 1 hour)
Expected: ~-1.0 hours
```

### Unit Testing (Future)

```cpp
// Example unit test structure
#include <QtTest>
class TestCalculations : public QObject {
    Q_OBJECT
private slots:
    void testNightBonusFullNight();
    void testNightBonusPartialNight();
    void testNightBonusDayOnly();
    void testRemainingTimePositive();
    void testRemainingTimeNegative();
    void testStatusDetermination();
};
```

---

## Documentation

### Code Documentation

Every public function should have:

```cpp
/**
 * @brief Brief one-line description
 * 
 * Detailed description of what the function does.
 * Explain algorithm if complex.
 * 
 * @param paramName Description of parameter
 * @param anotherParam Description
 * @return Description of return value
 * 
 * @throws ExceptionType When this exception is thrown
 * 
 * @see relatedFunction
 * @note Important note about usage
 * @warning Warning about edge cases
 * 
 * Example:
 * @code
 * double bonus = calculateNightBonus(startTime, 6);
 * qDebug() << "Bonus:" << bonus << "hours";
 * @endcode
 */
double calculateNightBonus(const QDateTime &startTime, int durationHours);
```

### README Updates

When adding features, update README.md:

- Add to Features section
- Update Usage instructions
- Add to Calculation Logic section
- Include examples

### CHANGELOG

Maintain CHANGELOG.md:

```markdown
## [Unreleased]
### Added
- Member discount calculation feature

### Changed
- Improved night bonus algorithm for multi-day rentals

### Fixed
- Bonus calculation error for sessions crossing midnight

## [1.0.0] - 2024-11-01
### Added
- Initial release
- Night bonus calculation
- Remaining time tracking
- Status indicators
```

---

## Pull Request Process

### Before Submitting

- [ ] Code follows style guide
- [ ] All tests pass
- [ ] Documentation updated
- [ ] No merge conflicts with develop branch
- [ ] Commit messages are clear
- [ ] PR description is complete

### PR Template

```markdown
## Description
Brief description of changes.

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Breaking change
- [ ] Documentation update

## Motivation
Why is this change needed?

## Changes Made
- Change 1
- Change 2
- Change 3

## Testing
How was this tested?

## Screenshots
If applicable.

## Checklist
- [ ] Code follows style guide
- [ ] Self-review completed
- [ ] Comments added for complex code
- [ ] Documentation updated
- [ ] No new warnings
- [ ] Tests added/updated
```

### Review Process

1. **Automated Checks** (if configured)
   - Build succeeds
   - Tests pass
   - No style violations

2. **Code Review**
   - Maintainer reviews code
   - Feedback provided
   - Requested changes made

3. **Approval & Merge**
   - At least 1 approval required
   - Squash and merge to develop
   - PR branch deleted

### After Merge

- Your contribution will be in next release
- You'll be added to CONTRIBUTORS.md
- Close related issues

---

## Community

### Communication Channels

- **GitHub Issues**: Bug reports, feature requests
- **GitHub Discussions**: Questions, ideas, show & tell
- **Pull Requests**: Code reviews
- **Email**: maintainer@example.com

### Recognition

Contributors akan diakui di:

- CONTRIBUTORS.md file
- Release notes
- Documentation (jika significant contribution)

### Questions?

Jangan ragu untuk bertanya:

1. Check existing documentation
2. Search existing issues/discussions
3. Create new discussion jika tidak menemukan jawaban
4. Tag maintainer jika urgent

---

## License

By contributing, you agree that your contributions will be licensed under the MIT License.

---

## Thank You! 🎉

Thank you for contributing to Rental PlayStation Management System!

Every contribution, no matter how small, helps make this project better.

**Happy Coding!** 💻✨
